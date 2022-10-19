#!/bin/bash
set -x
set -eou
# Build
# "make all" for example# Publish on github
echo "Publishing on Github..."
token="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"
#tag=$(git describe --tags)
tag="1.0.1"
#message="$(git for-each-ref refs/tags/$tag --format='%(contents)')"
message="My first message"
name=$(echo "$message" | head -n1)
description=$(echo "$message" | tail -n +3)
description=$(echo "$description" | sed -z 's/\n/\\n/g') # Escape line breaks to prevent json parsing problems# Create a release
#release="1.0.0"
release=$(curl -XPOST -H "Authorization:token $token" --data "{\"tag_name\": \"$tag\", \"target_commitish\": \"main\", \"name\": \"$name\", \"body\": \"$description\", \"draft\": false, \"prerelease\": true}" https://api.github.com/repos/plugosh/Simulation_Program/releases)
id="80360620"
#id=$(echo "$release" | sed -n -e 's/"id":\ \([0-9]\+\),/\1/p' | head -n 1 | sed 's/[[:blank:]]//g')
curl -XPOST -H "Authorization:token $token" -H "Content-Type:application/octet-stream" --data-binary @artifact.zip https://uploads.github.com/repos/plugosh/Simulation_Program/releases/$id/assets?name=artifact.zip
