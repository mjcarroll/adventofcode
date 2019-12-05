#!/usr/bin/env python3

import os
import requests

from datetime import datetime

class Downloader(object):
    def __init__(self, session):
        self.SESSION = session
        self.URL = 'https://adventofcode.com/{year}/day/{day}/input'

    def exists(self, year, day):
        path = f'./{year}/input/{day:02}.txt'
        return os.path.exists(path)

    def download(self, year, day):
        path = './{year}/input/'.format(year=year)
        if not os.path.exists(path):
            print("Creating: ", path)
            os.makedirs(path)

        cookies = {'session': self.SESSION}
        url = self.URL.format(year=year,day=day)
        r = requests.get(url, cookies=cookies)

        with open(os.path.join(path, f'{day:02}.txt'), 'w') as f:
            f.write(r.content.decode())

if __name__ == '__main__':
    cookie = '53616c7465645f5fd63809d875446feecbb8cde2f0651acbaef5879fd2f2101ed5431c53e5b6ecbbd590f252eec9fabe'

    d = Downloader(cookie)

    for year in range(2015, 2019):
        for day in range(1, 26):
            if not d.exists(year, day):
                d.download(year, day)
            else:
                print(f'Skipping {year} day {day}')

    kickoff = datetime(year=2019, month=11, day=30, hour=23, minute=0)

    dayNum = (datetime.now() - kickoff).days + 1

    year = 2019
    for day in range(1, dayNum + 1):
        if not d.exists(year, day):
            d.download(year, day)
        else:
            print(f'Skipping {year} day {day}')


