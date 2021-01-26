import gym_connect

if __name__ == "__main__":
    conn = gym_connect.GymConnector()
    for i in range(10):
        stats = conn.step(1e6)
        if stats:
            print(stats)
        else:
            break
    print("Exit Gym")