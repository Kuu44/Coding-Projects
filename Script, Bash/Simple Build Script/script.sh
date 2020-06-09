#!/bin/bash

echo "🔥🔥😎Building Kuu😎🔥🔥"

#Version Checking
firstline=$(head -n 1 source/changelog.md)
read -a splitfirstline <<< $firstline
version=${splitfirstline[1]}
echo "🏭Building Version:" $version

#Continue Checking
echo "Enter 1 to ✔ and 0 to ❌"
read versioncontinue
if [ $versioncontinue -eq 1 ]
  then
    for filename in source/*
      do
        if [ "$filename" == "source/secretinfo.md" ]
          then
            #Encrypting
            firstline=$(head -n 1 $filename)
            read -a splitfirstline <<< $firstline
            echo ${splitfirstline[0]} ${splitfirstline[1]} ${splitfirstline[2]} "XX" > build/secretinfo.md
          else
            echo "👷‍♂️ $filename 👷‍♂️"
            cp $filename build/
        fi
      done
  else
    echo "Comeback later"
fi
echo "Build version $version contains: "
ls build/
#gzip -k -N build/ 
tar -cvzf Build.gz  build/
#
cd build/
#Add code later
cd ..

