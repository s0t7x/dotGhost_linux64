#!/bin/sh

if git pull | grep -q 'Already up to date.'; then
  echo "Nothing to update, exiting..."
  exit
fi