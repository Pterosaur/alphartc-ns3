#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym_process
import gym_connect

import zmq

import pytest

@pytest.mark.timeout(1.5)
def test_base():
    proc = gym_process.GymProcess(gym_id = "test_gym", report_interval_ms=60, duration_time_ms=1000)
    conn = gym_connect.GymConnector(gym_id = "test_gym")
    all_stats = []
    while True:
        stats = conn.step(1e9)
        if stats == None:
            break
        all_stats += stats
    # stats shouldn't be empty
    assert(all_stats)
    assert(proc.wait() == 0)
