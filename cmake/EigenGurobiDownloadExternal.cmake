include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
  set(EIGEN_GUROBI_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
  set(EIGEN_GUROBI_EXTRA_OPTIONS "")
endif()

function(eigen_gurobi_download_project name)
  download_project(
    PROJ         ${name}
    SOURCE_DIR   ${EIGEN_GUROBI_EXTERNAL}/${name}
    DOWNLOAD_DIR ${EIGEN_GUROBI_EXTERNAL}/.cache/${name}
    QUIET
    ${EIGEN_GUROBI_EXTRA_OPTIONS}
    ${ARGN}
  )
endfunction()

################################################################################

# Eigen
function(download_eigen)
	eigen_gurobi_download_project(eigen
		GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror
		GIT_TAG        3.3.7
	)
endfunction()

# Catch2
function(download_catch2)
    eigen_gurobi_download_project(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.11.0
    )
endfunction()
