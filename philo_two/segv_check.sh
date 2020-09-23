while [ 1 ]
  do
      sleep 1
      ./philo_two 199 400 200 200
      if [ "$?" -eq "139" ]; then
        echo 'segv'
        exit 1
      fi
      sleep 1
      ./philo_two 199 800 200 200 1
      if [ "$?" -eq "139" ]; then
        echo 'segv'
        exit 1
      fi
  done
