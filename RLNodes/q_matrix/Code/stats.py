#!/usr/bin/env python
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


# global 
cnt = 0
states = []
rewards = [[]]
actions = []
sorted_states = np.arange(8)
path = '/home/user/workspace/src/ReinforcementLearningByElisabeth/RLNodes/q_matrix/stats/'
  
# set info
def set_info(state, reward, action):
    global states, rewards, actions
    states.append(state)
    rewards[cnt].append(reward)
    actions.append(action)
    
# sort states into array
def sort_states():
    global states, sorted_states
    st = np.array(states)
    for i in range(8):
        sorted_states[i] = np.count_nonzero(st == i)
        
def get_cumulative_reward():
    global rewards 
    res = []
    for i in range(len(rewards)):
        res.append(np.sum(rewards[i]))
    return res
    
# create diagrams
def create_diagrams():
    global states, rewards, actions 
    global sorted_states
    global path
    global cnt
    
    print("CREATED DIAGRAM")
    
    # states 
    plt.figure()
    poss_states = ['0', '1', '2', '3', '4', '5', '6', '7']
    sort_states()
    plt.bar(poss_states, sorted_states)
    plt.ylabel('Number of times agent being in state')
    plt.xlabel('States')
    path_1 = path + 'states' + str(cnt) + '.png'
    if((cnt % 10 == 0) or (cnt == 1)):
        plt.savefig(path_1)
    plt.close()
    
    # cumulative reward per episode
    plt.figure()
    cumulative_rew = get_cumulative_reward()
    plt.plot(cumulative_rew)
    plt.ylabel('Cumulative Rewards')
    plt.xlabel('Episode')
    path_2 = path + 'rew_p_act' + str(cnt) + '.png'
    if((cnt % 10 == 0) or (cnt == 1)):
        plt.savefig(path_2)
    plt.close()
    
    cnt += 1
    rewards.append([])
