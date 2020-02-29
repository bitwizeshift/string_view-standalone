#!/usr/bin/env bash
################################################################################
# Travis-CI : deploy-conan
# ------------------------
#
# Builds and deploys a conan project
#
# Environment:
#  BINTRAY_REMOTE_URL : The URL to push the deployed packages to
#  BINTRAY_USERNAME   : The username of the bintray user that pushes packages
#  BINTRAY_API_KEY    : The API key that corresponds to the bintray user
################################################################################

set -e

test_path="$(pwd)/.conan/test_package"
conanfile_path="$(pwd)"
remote="destination_remote"

package_name="string_view_standalone"
user="StringViewStandalone"

version=$(conan inspect "${conanfile_path}" --attribute version | sed 's@version: @@g')
full_package="${user}/${version}@${package_name}/stable"

# Create and test the package
conan create . "${package_name}/stable"
conan test "${test_path}" "${full_package}"

# Set up the user information for uploading
conan remote add ${remote} ${BINTRAY_REMOTE_URL}
conan user -p ${BINTRAY_API_KEY} -r ${remote} ${BINTRAY_USERNAME}
conan upload "${full_package}" -r ${remote} --all