library(Rcpp)
sourceCpp("simulate_human_shuffle.cpp")


collect_input <- function(){
  cat("Please input the lengths of your runs as prompted. Please only input positive integer values. \n") 
  cat("If your longest run length is greater than 20, please reshuffle and try again. \n")
  cat("After you input the number of runs of your maximum length, input '-1' as the next value, and the data collection will stop. \n")
  my_longrun <- vector(mode = "integer")
  
  for(i in 1:20){
    repeat{
      value <- readline(prompt = paste0("Number of runs of legnth ", i, ": "))
      int_value <- suppressWarnings(as.numeric(value))
      if (!is.na(int_value) && int_value == -1) {
        break # This breaks the inner repeat loop
      }
      # Normal validation
      if (!is.na(int_value) && int_value >= 0) {
        break 
      } else {
        cat("Invalid input. Try again.\n")
      }
    }
    if (i == 20){
      cat("Maximum length of runs reached. If you have runs longer than 20, please reshuffle and try again.")
    }
    else if (!is.na(int_value) && int_value == -1) {
      cat("Stopping input collection. \n")
      break # This breaks the outer for loop
    }
    my_longrun[i] = int_value
  }
  return(my_longrun)
}

# check if total is 52 cards
check_run_input <- function(longrun){
  sum_runs = sum(seq_along(longrun) * longrun)
  if (sum_runs != 52){
    stop("Input of runs must sum to 52 total cards. Please restart.")
  }
  else{
    cat("Runs sum correctly! Your input is valid. Proceeding with calculations.")
  }
}


my_longrun<- collect_input()
check_run_input(my_longrun)


total_trials       <- 10000000     # 10 Million total trials per shuffle time

cat("Your final mean number of rising sequences was", mean(getRisingSequenceWithLongRun(total_trials, 1, my_longrun)))





