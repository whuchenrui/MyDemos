# coding=utf-8

import codecs
import csv
import json
import requests
import sys

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By


# Globals Variables
nsf_search_url = 'http://www.nsf.gov/awardsearch/simpleSearchResult?queryText='
nsf_csv_url = 'http://www.nsf.gov/awardsearch/ExportResultServlet?exportType=csv'
google_search_url = 'https://ajax.googleapis.com/ajax/services/search/web'
params = {'v': '1.0', 'rsz': 6}

# update set here
degree_list = ['doctor', 'Ph.D', 'J.D', 'M.D']


# Use selenium to simulate the browser, to avoid the requirement of cookies of nsf.gov website.
def fetch_csv():
    driver = webdriver.PhantomJS()
    driver.get(nsf_search_url + user_name)

    try:
        find_css = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CSS_SELECTOR, '.listview-item'))).text
        JSESSIONID = [c['value'] for c in driver.get_cookies() if c['name'] == 'JSESSIONID'][0]
        res = requests.get(nsf_csv_url, cookies={'JSESSIONID': JSESSIONID})

        if res.status_code != 200:
            print 'Due to the low connection speed, fetch nsf.gov csv file fail, please try again'
            return False
        else:
            with codecs.open(user_name+'.csv', 'w', 'utf-8') as fout:
                fout.write(res.text)
            print 'Fetch nsf.gov csv file success !  Saved as csv file in solution folder. '
            return True

    except Exception as e:
        print e
        print 'Internet connection not stable, please try again'
        return False


# get input user's investigators list from csv file
def csv_reader():
    investigator_list = []
    try:
        with open(user_name+'.csv') as fin:
            reader = csv.DictReader(fin)

            for row in reader:
                if row['ProgramManager'] is not None:
                    if user_name in row['ProgramManager']:
                        investigator_list.append(row['PrincipalInvestigator'])

        with codecs.open(user_name+'_investigators.txt', 'w', 'utf-8') as tmp:
            tmp.write(str(investigator_list))

    except Exception as e:
        print e

    return investigator_list


# check whether the user has phd degree on the linkedin page
# step1: use google search to find the user linkedin page
# step2: get the top 1 user linked page, and check whether he has phd or not
def is_phd_degree(name):
    params['q'] = 'url:linkedin.com/in ' + name

    req = requests.get(google_search_url, params=params)
    json_data = json.loads(req.text)

    linked_url = None
    try:
        if json_data is None or json_data['responseData'] is None or json_data['responseData']['results'] is None:
            return False

        for r in json_data['responseData']['results']:
            if 'linkedin.com/in' in r['url']:
                linked_url = r['url']
                break

        if linked_url is None:           # cannot find the user linkedin page
            return False
        else:
            print linked_url
            target_driver.get(linked_url)
            education_data = WebDriverWait(target_driver, 10).until(
                EC.presence_of_element_located((By.CSS_SELECTOR, '#education .schools'))
            ).text
            if education_data is None:   # have no access to education data
                return False
            for degree in degree_list:
                if degree in education_data:
                    return True
            return False
    except Exception as e:
        print 'Url', linked_url
        print e


# iterator all the investigators.
def fetch_linkedin_data(target_list):
    result_dict = {}
    global target_driver
    target_driver = webdriver.PhantomJS()

    for user in target_list:
        if user is not None:
            if is_phd_degree(user):
                print 'Yes'
                result_dict[user] = 'Yes'
            else:
                result_dict[user] = 'Not found'
    print result_dict
    target_driver.close()

    try:
        with open(user_name+'_degree_result.txt', 'w') as tmp:
            for each in result_dict:
                line = "{:<30}{:<10}".format(each, result_dict[each])
                tmp.write(line + '\n')
    except Exception as e:
        print e
        print "write to file error, please try again! "


def run():
    status = fetch_csv()
    if status:
        users = csv_reader()
        fetch_linkedin_data(users)
        print 'Get principal investigator degree successfully !'


if __name__ == "__main__":
    user_name = ""
    target_driver = None

    if len(sys.argv) < 2:
        print 'Wrong input, should be like: python solution.py full user name. '
        print 'Name is separated by one white space. '
    else:
        for i in sys.argv[1:]:
            user_name += ' ' + i
        user_name = user_name.strip()
        print 'Your are trying to search:', user_name
        run()
