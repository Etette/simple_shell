#!/bin/bash
#original source: https://github.com/Etette/simple_shell/generate-authors.sh
set -e

#cd "$(dirname "$(readlink -f "BASH_SOURCE")")/.."

{
	cat << 'EOH'
	# This file list individuals that contributed to this project.
	EOH
	echo
	git log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf
} > AUTHORS
