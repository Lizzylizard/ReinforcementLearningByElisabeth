#!/usr/bin/env python
import numpy as np
import matplotlib
import pickle

matplotlib.use('Agg')
import matplotlib.pyplot as plt

# global
cnt = 0
states = []
rewards = [[]]
actions = []
sorted_states = np.arange(8)
path = '/home/user/workspace/src/ReinforcementLearningByElisabeth/RLNodes/SingleDQN/dqn_keras_1/stats/'


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

def save_records():
  global rewards, states, actions, path

  try:
    # open correct file
    f = open(path + "actions_states_rewards.txt",
      "w")

    # pretty print matrix
    string = "actions = \n"
    string += str(actions)
    string += "\n\n"

    string += "states = \n"
    string += str(states)
    string += "\n\n"

    string += "rewards = \n"
    string += str(rewards)

    # write into file
    f.write(string)

    # close file
    f.close()
  except Exception as e:
    print(str(e) + "\nFile not written")

  with open (path + "reward_arr", 'wb') as fp:
    pickle.dump(rewards, fp)

  with open (path + "action_arr", 'wb') as fp2:
    pickle.dump(actions, fp2)

  with open (path + "states_arr", 'wb') as fp3:
    pickle.dump(actions, fp3)

  '''
  with open(path + 'reward_arr', 'rb') as fp4:
    saved_rewards = pickle.load(fp4)

  print("Rewards = " + str(rewards))
  print("Saved rewards = " + str(saved_rewards))
  '''

# create diagrams
def create_diagrams():
  global states, rewards, actions
  global sorted_states
  global path
  global cnt

  # print("CREATED DIAGRAM")

  '''
  # states
  plt.figure()
  poss_states = ['0', '1', '2', '3', '4', '5', '6', '7']
  sort_states()
  plt.bar(poss_states, sorted_states)
  plt.ylabel('Number of times agent being in state')
  plt.xlabel('States')
  path_1 = path + 'states' + str(cnt) + '.png'
  if ((cnt % 10 == 0) or (cnt == 1)):
    plt.savefig(path_1)
  plt.close()
  '''

  # cumulative reward per episode
  plt.figure()
  cumulative_rew = get_cumulative_reward()
  plt.plot(cumulative_rew)
  plt.ylabel('Cumulative Rewards')
  plt.xlabel('Episode')
  path_2 = path + 'reward_per_episode' + str(cnt) + '.png'
  #if ((cnt % 10 == 0) or (cnt == 1)):
  plt.savefig(path_2)
  plt.close()

  cnt += 1
  rewards.append([])
