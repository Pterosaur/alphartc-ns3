#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym_process
import gym_connect

import zmq

import pytest

@pytest.mark.timeout(5.5)
def test_base():
    proc = gym_process.GymProcess(gym_id = "test_gym", report_interval_ms=60, duration_time_ms=5000)
    conn = gym_connect.GymConnector(gym_id = "test_gym")
    while True:
        if conn.step(1e9) == None:
            break
    assert(proc.wait() == 0)
