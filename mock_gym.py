#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym_connect

if __name__ == "__main__":
    conn = gym_connect.GymConnector("gym")
    while True:
        stats = conn.step(1e6)
        if stats != None:
            print(stats)
        else:
            break
    print("Exit Gym")