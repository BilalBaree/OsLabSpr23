#!/bin/sh
netstat >> Log.txt
mail -s "Os Lab" -A Log.txt k213582@nu.edu.pk
