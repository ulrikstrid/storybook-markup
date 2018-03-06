#!/bin/bash
otp="$1"

echo "building project..."
yarn run build

echo "removing old temp dir..."
rm -rf temp

echo "creating temp dir..."
mkdir temp

echo "moving js files..."
cp lib/js/src/* temp
cp package.json temp/package.json

echo "moving reason files..."
cp -r src temp
cp bsconfig.json temp/bsconfig.json

echo "staring publish..."

cd temp
npm publish --otp="$otp"

echo "done."
