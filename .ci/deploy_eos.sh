#!/bin/sh -ie

REPO_NAME=$1
ARTIFACT_DIR=$2

# ## normally taken from the gitlab CI job
# EOS_BASE_WEB_DIR=/eos/project/c/cmsgemdaq/www
# EOS_COMMON_WEB_DIR=cmsgemdaq
# EOS_SITE_WEB_DIR=${EOS_BASE_WEB_DIR}/${REPO_NAME}
# EOS_SW_DIR=${EOS_BASE_WEB_DIR}/sw/${REPO_NAME}
# EOS_DOC_DIR=${EOS_BASE_WEB_DIR}/docs/${REPO_NAME}
# EOS_LATEST_DIR=${EOS_SW_DIR}/unstable
# EOS_RELEASE_DIR=${EOS_SW_DIR}/releases
# EOS_DOC_DIR_NAME=api
# EOS_REPO_DIR_NAME=repos

BUILD_VER=$(${BUILD_HOME}/${REPO_NAME}/config/build/tag2rel.sh | \
                   awk '{split($$0,a," "); print a[5];}' | \
                   awk '{split($$0,b,":"); print b[2];}')
BUILD_TAG=$(${BUILD_HOME}/${REPO_NAME}/config/build/tag2rel.sh | \
                   awk '{split($$0,a," "); print a[8];}' | \
                   awk '{split($$0,b,":"); print b[2];}')

REL_VERSION=${BUILD_VER%.*}

## from https://gist.github.com/jsturdy/a9cbc64c947364a01057a1d40e228452
# ├── index.html
# ├── sw
# │   ├── ${REPO_NAME}
# │   │   ├── latest/unstable ## all builds not on a release branch?
# │   │   |   ├── api/docs
# │   │   |   |    └── latest  ## overwrite with latest each build?
# │   │   |   └── repos
# │   │   |       └── ${ARCH} ## (slc6_x86_64/centos7_x86_64/centos8_x86_64/arm/peta/noarch/pythonX.Y/gccXYZ/clangXYZ?)
# │   │   |          ├── RPMS  ## keep all versions, manual cleanup only?
# │   │   |          │   └── repodata
# │   │   |          └── SRPMS  ## necessary?
# │   │   |              └── repodata
# │   │   └── releases
# │   │       ├── api/docs
# │   │       |   └── ${REL_VERSION} ## Maj.Min, might even not have this directory?
# │   │       |       ├── latest -> ${REL_VERSION}.Z+2
# │   │       |       ├── ${REL_VERSION}.Z+2
# │   │       |       ├── ${REL_VERSION}.Z+1
# │   │       |       └── ${REL_VERSION}.Z
# │   │       └── repos
# │   │           └── ${REL_VERSION} ## Maj.Min
# │   │               └── ${ARCH} ## (slc6_x86_64/centos7_x86_64/centos8_x86_64/arm/peta/noarch/pythonX.Y/gccXYZ/clangXYZ?)
# │   │                   ├── base
# │   │                   │   ├── RPMS
# │   │                   │   │   └── repodata
# │   │                   │   └── SRPMS
# │   │                   │       └── repodata
# │   │                   └── testing ## all untagged builds along a given release tree
# │   │                       ├── RPMS
# │   │                       │   └── repodata
# │   │                       └── SRPMS
# │   │                           └── repodata
############### BEGIN OR
# │   │   └── releases
# │   │       └── ${REL_VERSION} ## Maj.Min
# │   │           ├── api/docs
# │   │           │    └── latest -> ${REL_VERSION}.Z+2
# │   │           │    └── ${REL_VERSION}.Z+2
# │   │           │    └── ${REL_VERSION}.Z+1
# │   │           │    └── ${REL_VERSION}.Z
# │   │           └── repos
# │   │               └── ${ARCH} ## (slc6_x86_64/centos7_x86_64/centos8_x86_64/arm/peta/noarch/pythonX.Y/gccXYZ/clangXYZ?)
# │   │                   ├── base
# │   │                   │   ├── RPMS
# │   │                   │   │   └── repodata
# │   │                   │   └── SRPMS
# │   │                   │       └── repodata
# │   │                   └── testing ## all untagged builds along a given release tree
# │   │                       ├── RPMS
# │   │                       │   └── repodata
# │   │                       └── SRPMS
# │   │                           └── repodata
# │   └── extras ## holds all extra/external packages we build for compatibility
# |       └── ${ARCH} ## (slc6_x86_64/centos7_x86_64/centos8_x86_64/arm/peta/noarch/pythonX.Y/gccXYZ/clangXYZ?)
# │           └── RPMS
# │               └── repodata
# ├── guides ## user/developer guides and other synthesied information, if versioning of this is foreseen, need to address
# │   ├── user
# |   |   └── index.html
# │   └── developers
# |       └── index.html
# └── docs
#     ├── index.html
#     └── ${REPO_NAME} ## one for each repo, this would be he entry point to the versioned
#         ├── index.html
#         ├── unstable ## filled from `develop` or symlink to the above `api/latest`
#         ├── latest ## filled from last tagged build, or as a symlink to releases/M.M/api/latest
#         └── styles/scripts/css/js  ## styles that we will not change

RELEASE_DIR=${EOS_RELEASE_DIR}/${REL_VERSION}

##### RPMs
ARCH='arch' ## FIXME, job dependent

echo "Figuring out appropriate tag"
## choose the correct of: base|testing|latest/unstable
if [[ ${BUILD_TAG} =~ (dev) ]]
then
    ## unstable for unknown or untagged
    DEPLOY_DIR=${EOS_LATEST_DIR}
    DOCS_DIR=${DEPLOY_DIR}/${EOS_DOC_DIR_NAME}
    TAG_REPO_TYPE=unstable
    REPO_DIR=${DEPLOY_DIR}/${EOS_REPO_DIR_NAME}/${ARCH}
elif [[ ${BUILD_TAG} =~ (alpha|beta|pre|rc) ]]
then
    ## testing for tag vx.y.z-(alpha|beta|pre|rc)\d+-git<hash>
    DEPLOY_DIR=${EOS_RELEASE_DIR}/${REL_VERSION}
    DOCS_DIR=${DEPLOY_DIR}/${EOS_DOC_DIR_NAME}
    TAG_REPO_TYPE=testing
    REPO_DIR=${DEPLOY_DIR}/${EOS_REPO_DIR_NAME}/${ARCH}/testing
elif [[ ${BUILD_VER} =~ [0-9]$ ]]
then
    ## base for tag vx.y.z
    DEPLOY_DIR=${EOS_RELEASE_DIR}/${REL_VERSION}
    DOCS_DIR=${DEPLOY_DIR}/${EOS_DOC_DIR_NAME}
    TAG_REPO_TYPE=base
    REPO_DIR=${DEPLOY_DIR}/${EOS_REPO_DIR_NAME}/${ARCH}/base
else
    ## unstable for unknown or untagged
    DEPLOY_DIR=${EOS_LATEST_DIR}
    DOCS_DIR=${DEPLOY_DIR}/${EOS_DOC_DIR_NAME}
    TAG_REPO_TYPE=unstable
    REPO_DIR=${DEPLOY_DIR}/${EOS_REPO_DIR_NAME}/${ARCH}
fi

echo mkdir -p ${DOCS_DIR}
echo mkdir -p ${REPO_DIR}/{RPMS,SRPMS}
echo "Done creating repository structure"

echo "Tag ${BUILD_VER}${BUILD_TAG} determined to be ${TAG_REPO_TYPE}"

CI_REPO_DIR=${REPO_DIR}
echo mkdir ${ARTIFACT_DIR}/done

## if unstable, rsync docs with --delete
## source RPM
echo rsync ${ARTIFACT_DIR}/*.src.rpm  ${KRB_USERNAME}@lxplus:${CI_REPO_DIR}/SRPMS
echo mv    ${ARTIFACT_DIR}/*.src.rpm  ${ARTIFACT_DIR}/done

## primary RPM, devel RPM, and debuginfo RPM
echo rsync ${ARTIFACT_DIR}/*-debuginfo*.rpm  ${KRB_USERNAME}@lxplus:${CI_REPO_DIR}/RPMS
echo mv    ${ARTIFACT_DIR}/*-debuginfo*.rpm  ${ARTIFACT_DIR}/done
echo rsync ${ARTIFACT_DIR}/*-devel*.rpm      ${KRB_USERNAME}@lxplus:${CI_REPO_DIR}/RPMS
echo mv    ${ARTIFACT_DIR}/*-devel*.rpm      ${ARTIFACT_DIR}/done
echo rsync ${ARTIFACT_DIR}/*.rpm             ${KRB_USERNAME}@lxplus:${CI_REPO_DIR}/RPMS

## update the repositories
echo "Updating the repository"
echo createrepo --update ${CI_REPO_DIR}/RPMS
echo createrepo --update ${CI_REPO_DIR}/SRPMS

## update the groups?

##### Documentation, only done for final tags?
echo "Publishing documentation"
CI_DOCS_DIR=${DOCS_DIR}
if [ -n "${BUILD_TAG}" ]
then
    TAG_DOC_DIR=${CI_DOCS_DIR}/${BUILD_VER}
    LATEST_DOC_DIR=${RELEASE_DIR}/api/latest
    LATEST_DOC_DIR=${EOS_DOC_DIR}/latest
    echo rsync ${ARTIFACT_DIR}/doc/html/ --delete ${KRB_USERNAME}@lxplus:${TAG_DOC_DIR}
    echo "ln -sf ${TAG_DOC_DIR} ${LATEST_DOC_DIR}"
    ## update the index file?
    ## or have the landing page running some scripts querying the git tags, populating some JSON, and dynamically adapting the content
else
    TAG_DOC_DIR=${CI_DOCS_DIR}
    LATEST_DOC_DIR=${EOS_DOC_DIR}/unstable
    echo rsync ${ARTIFACT_DIR}/doc/html/ --delete ${KRB_USERNAME}@lxplus:${TAG_DOC_DIR}
    echo "ln -sf ${TAG_DOC_DIR} ${LATEST_DOC_DIR}"
    ## update the index file?
    ## or have the landing page running some scripts querying the git tags, populating some JSON, and dynamically adapting the content
fi

