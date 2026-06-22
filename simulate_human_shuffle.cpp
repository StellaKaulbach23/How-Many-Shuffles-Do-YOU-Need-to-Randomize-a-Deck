#include <Rcpp.h>
#include <vector>
#include <random>
#include <cstdio>
#include <numeric>   // Required for std::accumulate
#include <algorithm> // Required for std::copy and std::upper_bound

using namespace Rcpp;

// [[Rcpp::export]]
// Note: we check that longrun correctly sums to 52 before it is input here
// We assume longrun has the structure that the value at each index is the number of runs of length "index"
IntegerVector getRisingSequenceWithLongRun(int trials, int k_shuffles, IntegerVector longrun) {
  if (k_shuffles >= 20){
    Rcpp::stop("The number of shuffles necessary for your input has exceeded 20 shuffles. Please try again.");
  }
  
  printf("\n Starting calculations for k = %d \n", k_shuffles);
  double goal_mean = 24.71046348;
  
  IntegerVector results(trials);
  
  int masterDeck[52];
  int rightHand[52];
  int leftHand[52];
  int cardPositions[53];

  size_t longrun_size = longrun.size();
  
  // get proportions of run lengths
  double total_sum = std::accumulate(longrun.begin(), longrun.end(), 0.0);
  std::vector<double> props(longrun_size); //this faster than Rccp::..
  double cumulative_sum = 0.0;
  for (size_t i = 0; i < longrun_size; ++i) {
    cumulative_sum += longrun[i] / total_sum;
    props[i] = cumulative_sum;
  }
  
  //get all random in a vector first to speed up
  int pool_size = 1000000; // 1 million elements (8MB)
  NumericVector rand_pool = Rcpp::runif(pool_size);
  int rand_idx = 0;
  
  int mpos = 0, rpos = 0, lpos = 0;
  int r_size = 0, l_size = 0;
  
  for (int t = 0; t < trials; ++t) {
    if(t == 10000 || t == 100000 || t == 1000000){
      Rcpp::IntegerVector temp = results[Rcpp::Range(0, t-1)];
      double curr_mean = Rcpp::mean(temp);
      double curr_sd = std::sqrt(Rcpp::var(temp));
      double se = curr_sd / sqrt(t);
      double lwr = curr_mean - 1.96*se;
      double upr = curr_mean + 1.96*se;
      
      printf("At k = %d shuffles, we estimate that your true number of rising sequences is between %f < true mean <  %f \n", k_shuffles, lwr, upr);
      
      if(upr < goal_mean){
        printf("Your range is too far from goal mean of %.2f, moving forward to next k. \n", goal_mean);
        return getRisingSequenceWithLongRun(trials, (k_shuffles+1), longrun);
      }
    }
    
    
    // 1.Each trial start with a new ordered masterdeck
    for (int i = 0; i < 52; ++i) {
      masterDeck[i] = i + 1;
    }
    
    // 2. EXECUTE THE K SHUFFLES
    for (int shuffle = 0; shuffle < k_shuffles; ++shuffle) {
      
      // get split between L and R hand cards
      int cutpoint = R::rbinom(52, 0.5);
      
      // physically separate deck, copy cards to left and right hand arrasy based on cutpoint
      std::copy(masterDeck, masterDeck + cutpoint, rightHand);
      std::copy(masterDeck + cutpoint, masterDeck + 52, leftHand);
      
      r_size = cutpoint;
      l_size = 52-cutpoint;
      
      mpos = 0; 
      rpos = 0; 
      lpos = 0;
      
      
      int start_hand = R::rbinom(1, 0.5); // 0 = LH, 1 = RH
      
      
        
      while(mpos < 52){
        
        //refill random number pool if ran out
        if (rand_idx >= pool_size) {
          rand_pool = Rcpp::runif(pool_size);
          rand_idx = 0;
        }
        //grab one random number from the pool
        double u = rand_pool[rand_idx++];
        
        
        auto it = std::upper_bound(props.begin(), props.end(), u); //binary search
        int draw = std::distance(props.begin(), it) + 1; //it (memory pointer) converted back to index
        //These two lines code above is to replace the function down there, using binary search instead of linear search
        
        
        for (int i = 0; i < draw; ++i) {
          // check if one of the hands is empty midway thro a clump
          // will kick out of this inner for loop and hit the saftey check
          // at the beginning of the outer while loop
          if(mpos >= 52 || rpos >= r_size || lpos >= l_size) break;
          
          if(start_hand == 1){
            if(mpos >= 52 || rpos >= r_size) break;
            masterDeck[mpos++] = rightHand[rpos++];
          } else if(start_hand == 0){
            if(mpos >= 52 || lpos >= l_size) break;
            masterDeck[mpos++] = leftHand[lpos++];
          }
        }
        start_hand = 1 - start_hand;
        
        
        if(rpos >= r_size || lpos >= l_size){
          while (mpos < 52 && rpos < r_size) {
            masterDeck[mpos++] = rightHand[rpos++];
          }
          while (mpos < 52 && lpos < l_size) {
            masterDeck[mpos++] = leftHand[lpos++];
          }
          break;
        }
        
      }
    

    }
  
   // printf("Current Deck Order: ");
   // for (int i = 0; i < 52; ++i) {
   //  printf("%d ", masterDeck[i]);
   // }
   // printf("\n");
   // fflush(stdout);
    
    // 3. count rising sequence after k shuffle
    for (int i = 0; i < 52; ++i) {
      cardPositions[masterDeck[i]] = i;
    }
    
    
    int risingSequences = 1;
    for (int v = 1; v < 52; ++v) {
      if (cardPositions[v + 1] < cardPositions[v]) {
        risingSequences++;
      }
    }
    
    results[t] = risingSequences; // Store the score for this trial
  }
  
  double curr_mean = Rcpp::mean(results);
  if (curr_mean < goal_mean){
    return getRisingSequenceWithLongRun(trials, (k_shuffles+1), longrun);
  }
  
  
  
  printf("Final Result: You need k = %d shuffles to reach an equally good (or better) level of randomness as described by Bayer and Diaconis (1992). \n", k_shuffles);
  return results;
}
