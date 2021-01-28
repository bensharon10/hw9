#!/bin/bash

cat $1 | while read line;
	do
		clean_line = `sed 's/ //g' line`;
		if [[ ${clean_line:0:1} != '#' ]]
		then
			echo $clean_line >& legal_rules;
		fi
done

cat legal_rules | while read line;
	do ./firewall.exe $line > legal_packets;
done
