function(cpput_add_external_git_project)
    set(options NOBUILD)
    set(oneValueArgs TARGET_NAME PROJECT_DIR)
    set(multiValueArgs CMAKE_ARGS)
    cmake_parse_arguments("CPPUT" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )


    set (EXTERNAL_PROJECT_PARAMETERS
        ${CPPUT_TARGET_NAME}
        DOWNLOAD_DIR    "${CPPUT_PROJECT_DIR}"
        SOURCE_DIR      "${CPPUT_PROJECT_DIR}"
        STEP_TARGETS    download)


    if (CPPUT_NOBUILD)
        list(APPEND EXTERNAL_PROJECT_PARAMETERS
            BUILD_COMMAND       ""
            INSTALL_COMMAND     ""
            CONFIGURE_COMMAND   ""
        )
    else (CPPUT_NOBUILD)
        list(APPEND EXTERNAL_PROJECT_PARAMETERS
            CMAKE_ARGS      ${CPPUT_CMAKE_ARGS}
        )
    endif (CPPUT_NOBUILD)


    if (EXISTS "${CPPUT_PROJECT_DIR}/.git")
        message("Found '.git' subdirectory in project '${CPPUT_PROJECT_DIR}': skipping download step.")

        list(APPEND EXTERNAL_PROJECT_PARAMETERS
            DOWNLOAD_COMMAND    ""
        )
    else()
        find_package(Git)

        if (GIT_FOUND)
            list(APPEND EXTERNAL_PROJECT_PARAMETERS
                DOWNLOAD_COMMAND    ${GIT_EXECUTABLE} submodule update --init --no-fetch ./
            )
        else(GIT_FOUND)
            message( SEND_ERROR "Cannot download project '${CPPUT_PROJECT_DIR}' due to missing git. Checking if the files are alredy there..." )
            file(GLOB RESULT ${CPPUT_PROJECT_DIR})
            list(LENGTH RESULT RES_LEN)
            if(RES_LEN EQUAL 0)
                message(FATAL_ERROR "Project directory '${CPPUT_PROJECT_DIR}' is empty, compilation is impossible." )
            endif()
        endif(GIT_FOUND)
    endif()

    ExternalProject_Add(
        ${EXTERNAL_PROJECT_PARAMETERS}
    )
endfunction(cpput_add_external_git_project)
