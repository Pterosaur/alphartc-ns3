#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import gym_connect

import zmq

import threading
import pytest


def create_reply(conn_name: str):
    ctx = zmq.Context()
    sock = ctx.socket(zmq.REP)
    sock.bind(gym_connect.__ZMQ_TYPE_PREFIX__ + conn_name)
    return ctx, sock


def fill_reply(sock):
    def fill_reply_():
        bandwidth = sock.recv()
        assert(bandwidth.decode('utf-8').isnumeric())
        sock.send(b"{}")
        bandwidth = sock.recv()
        assert(bandwidth.decode('utf-8').isnumeric())
        sock.send(gym_connect.__GYM_EXIT_FLAG__)
    threading.Thread(target=fill_reply_).start()


@pytest.mark.timeout(1)
def test_reply_and_request():
    ctx, sock = create_reply("test_gym_connect")
    fill_reply(sock)
    conn = gym_connect.GymConnector("test_gym_connect")
    assert(conn.step(1000) is not None)
    assert(conn.step(1000) is None)


@pytest.mark.timeout(1)
def test_request_and_reply():
    conn = gym_connect.GymConnector("test_gym_connect")
    ctx, sock = create_reply("test_gym_connect")
    fill_reply(sock)
    assert(conn.step(1000) is not None)
    assert(conn.step(1000) is None)
