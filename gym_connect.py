import zmq
import json

__ZMQ_TYPE_PREFIX__ = "ipc:///tmp/"
__GYM_EXIT_FLAG__ = b"Bye"

class GymConnector(object):
    def __init__(self, connect_id = "gym"):
        self.connect_id = connect_id
        self.zmq_ctx = zmq.Context()
        self.zmq_sock = self.zmq_ctx.socket(zmq.REQ)
        self.zmq_sock.connect(__ZMQ_TYPE_PREFIX__ + self.connect_id)

    def step(self, bandwidth):
        self.zmq_sock.send_string(str(int(bandwidth)))
        rep = self.zmq_sock.recv()
        if rep == __GYM_EXIT_FLAG__:
            return None
        return json.loads(rep)

    def __del__(self):
        self.zmq_sock.disconnect(__ZMQ_TYPE_PREFIX__ + self.connect_id)
