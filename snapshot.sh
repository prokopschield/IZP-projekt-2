#!/bin/bash
mkdir snapshot
for file in *;
	do if [[ "$file" != "node_modules" ]]
		then if [[ "$file" != "snapshot" ]]
			then ln -s ../$file snapshot/$file;
		fi
	fi
done
for file in .*;
	do if [[ "$file" != ".git" ]]
		then if [[ "$file" != "." ]]
			then if [[ "$file" != ".." ]]
				then ln -s ../$file snapshot/$file;
			fi
		fi
	fi
done
nstore store snapshot/
rm -r snapshot/
