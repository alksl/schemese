#!/bin/sh

SESSION_NAME=schemese

if tmux has-session -t $SESSION_NAME
then
  tmux attach -t $SESSION_NAME
  exit
fi

tmux start-server
tmux new-session -d -s $SESSION_NAME
tmux rename-window 'Vim'
tmux send-keys 'vim' C-m
tmux split-window -t $SESSION_NAME:0 -h -p 30
tmux send-keys -t $SESSION_NAME:0 'cd build' C-m 'make && make test' C-m
tmux select-pane -t 0
tmux attach -t $SESSION_NAME
