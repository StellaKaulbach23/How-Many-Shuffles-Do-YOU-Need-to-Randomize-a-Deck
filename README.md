## **Project Abstract:**
Bayer and Diaconis determined that seven unbiased riffle shuffles are sufficient to randomize a deck of cards. Our study investigates whether the unbiased riffle model accurately describes human shuffling and how many shuffles an individual requires to achieve an equal level of randomness. 

To evaluate the unbiased riffle assumption, twenty volunteers shuffled decks of cards while recording the longest run length. We simulated unbiased riffle shuffles to obtain the null distribution of longest runs and compared each subject’s observed distribution to this theoretical model using Kolmogorov–Smirnov tests. The resulting p-values were combined to assess the overall accuracy of the unbiased riffle model compared to human shuffling behavior. Our analysis found that the unbiased riffle model does not adequately describe all human shufflers.

Thus, we developed a program that repeatedly simulates an individual’s shuffling style and measures the mean number of rising sequences after successive shuffles. We defined a threshold of sufficient randomness using the mean number of rising sequences after repeated trials of the seven unbiased riffle shuffles. We were then able to estimate the number of shuffles required for an individual to reach or exceed this threshold. 

These results demonstrate that the number of shuffles required to randomize a deck depends on an individual's shuffling habits and indicate that the standard recommendation of seven shuffles is not sufficient for everyone. Subjects typically required 7 to 12 shuffles to reach the randomness threshold. 

## **Instructions:**

To utilize our code to determine how many shuffles YOU need to randomize a deck of 52 cards, you will need to follow these steps. If you have trouble following these steps, there is an instructional video at the end of this section that contains an example/tutorial of the process.

**Step 1:** Shuffle a deck of 52 cards one time, starting with all the red cards in one hand and the black cards in another. Then, record the length of each "run" in the shuffled deck. A "run" is a grouping of consecutive cards of the same color, so the length of a run would be the number of consecutive cards of the same color before the appearence of a card of a different color (which marks the beginning of the next run). Once you have gotten all the way through the shuffled deck, count up how many runs of length 1, 2, 3, etc. you have. This will be your run length data.

**Step 2:** Import the files "human_input.R" and "simulate_human_shuffle.cpp" into RStudio. You can either download the files and then open them using RStudio or create a new project in RStudio using the link of this GitHub repository (recommended). This step is not featured in the tutorial video. Refer to the following link for help with this step. [Instructions to Create a RStudio Project from GitHub Repository](https://happygitwithr.com/existing-github-first#rstudio-ide-1).

**Step 3:** Once you have the files in RStudio, all you need to do is run the "human_input.R" file and input your run length data to get your presonalized results. Taking user input from the console in RStudio can be a bit finicky, and we have found that the best way to get the code to run as intended is using the following method. To run the code, click this button in the top left portion of the screen labeled "Source on Save". Once that box is checked, click the save button immediately to the left. The code should start running and prompting user input.

**Step 4:** Input your run length data as prompted, and once you have finished, input a "-1" to end the data collection. The code should start running simulations of k = 1, 2, 3, etc. shuffles. If you receive an error code at this step, you have either input data outside the acceptable range or input data that does not properly sum to 52. 

**Step 5:** Enjoy your results and share this project with your friends!

## **Video Tutorial:**

[Link to video tutorial on Google Drive](https://drive.google.com/file/d/13A-knL3liEd5TbMh1p1IPL6dIFdwUfTf/view?usp=sharing)

