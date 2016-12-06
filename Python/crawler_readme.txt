@author: Rui Chen
@date:   04/11/2016
@email:  chenray@umich.edu

How to run
Set up environment, need brew, phantomjs, selenium.
0: Enter the command line environment.
1: brew install phantomjs   (if not applicable, type brew update, then try again)
2: pip install selenium     (May need root authority)
3: change to solution folder, then type: python solution.py full_name  (full name are separated by one whitespace)

Input
1: intput the full name, separated by one whitespace
2: We can change the degree level in solution.py line 22.


Output
There will be three output files. (Use Steven Konsek as an example)
1: Steven Konsek.csv, data download from nsf.gov website, in csv format
2: Steven konsek_investigators.txt,  investigators of Steven Konsek, stored in a list.
3: degree_result.txt,  put result in txt file, for each row, start from full name, then whether he has phd degree.


Some clarifications:
1: strategy for this crawler is, first download the csv data based on the input, second, get all the investigators of
   this name. Third, for each investigator, use google search API to get the user's linkedin page. At last, check whether
   this page contains phd degree or not.
2: Why use selenium?  Because www.nsf.gov has some special ways to build the website, which results in the much difficulty
   to crawl the data. Technically, due to the cookies, we cannot easily get request data from the url directly. Thus we
   use selenium to simulate the browser, which successfully fix this problem.
3: Why not use linkedin API?  Because the education data is only available to Linkedin partner, which requires much more
   information and more than two weeks to be approved.
4: It is hard to identify the person on the website just by name, thus the result is not trustful. We try to lower the
   false rate by set the degree as Not found, instead of No. If the result is Yes, we have strong confidence that the
   result is reliable.
5: Due to the limitation of google search API, we have roughly 1000 times search per day.
6: For simplicity, the code is just runnable, but not strong enough. More work is needed.


Further improvement:
1: We can use more solid ways to identify the user, and use more than one source to judge the result.

Thanks! Enjoy this
