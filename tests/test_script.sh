#!/bin/bash
test_name=$1
source_dir=$2

# Execute the test
echo "Running ${1}"
./${test_name}
echo "Completed ${1}"

# Compute the hash
test_file="${test_name}.ppm"
test_md5="$(shasum ${test_file} | cut -f 1 -d ' ')"

# Get the hash from ground truth
golden_ref_md5="$(cat checksum.txt)"

# Compare the hashes
if [ "${test_md5}" != "${golden_ref_md5}" ]; then
    echo $test_md5
    echo $golden_ref_md5
    exit -1
fi

# Post test clean up on success (remove image files, executable, and checksum)
rm *.ppm checksum.txt ${test_name}
exit 0
