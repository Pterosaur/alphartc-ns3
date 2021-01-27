#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym

def test_basic():
    total_stats = []
    g = gym.Gym("test_gym")
    g.reset()
    while True:
        stats, flag = g.step(1000)
        if flag:
            total_stats += stats
        else:
            break
    assert(total_stats)

