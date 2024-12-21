function(property_reader_guard VARIABLE ACCESS VALUE CURRENT_LIST_FILE STACK)
    if("${PROPERTY_READER_GUARD_DISABLED}")
        return()
    endif()

    if("${ACCESS}" STREQUAL "MODIFIED_ACCESS")
        message(FATAL_ERROR
            " Variable ${VARIABLE} is not supposed to be changed.\n"
            " It is used only for reading target property ${VARIABLE}.\n"
            " Use\n"
            "     set_target_properties(\"<target>\" PROPERTIES \"${VARIABLE}\" \"<value>\")\n"
            " or\n"
            "     set_target_properties(\"<target>\" PROPERTIES \"${VARIABLE}_<CONFIG>\" \"<value>\")\n"
            " instead.\n")
    endif()
endfunction()

function(create_property_reader NAME)
    set(PROPERTY_READER_GUARD_DISABLED TRUE)
    set(CONFIG_VALUE "$<TARGET_GENEX_EVAL:${PROPS_TARGET},$<TARGET_PROPERTY:${PROPS_TARGET},${NAME}_$<UPPER_CASE:$<CONFIG>>>>")
    set(IS_CONFIG_VALUE_EMPTY "$<STREQUAL:${CONFIG_VALUE},>")
    set(GENERAL_VALUE "$<TARGET_GENEX_EVAL:${PROPS_TARGET},$<TARGET_PROPERTY:${PROPS_TARGET},${NAME}>>")
    set("${NAME}" "$<IF:${IS_CONFIG_VALUE_EMPTY},${GENERAL_VALUE},${CONFIG_VALUE}>" PARENT_SCOPE)
    variable_watch("${NAME}" property_reader_guard)
endfunction()

function(set_config_specific_property NAME VALUE)
    set_target_properties("${PROPS_TARGET}" PROPERTIES "${NAME}_${PROPS_CONFIG_U}" "${VALUE}")
endfunction()

create_property_reader("TARGET_NAME")
create_property_reader("OUTPUT_DIRECTORY")

set_config_specific_property("TARGET_NAME" "${PROPS_TARGET}")
set_config_specific_property("OUTPUT_NAME" "${TARGET_NAME}")
set_config_specific_property("ARCHIVE_OUTPUT_NAME" "${TARGET_NAME}")
set_config_specific_property("LIBRARY_OUTPUT_NAME" "${TARGET_NAME}")
set_config_specific_property("RUNTIME_OUTPUT_NAME" "${TARGET_NAME}")

set_config_specific_property("ARCHIVE_OUTPUT_DIRECTORY" "${OUTPUT_DIRECTORY}")
set_config_specific_property("LIBRARY_OUTPUT_DIRECTORY" "${OUTPUT_DIRECTORY}")
set_config_specific_property("RUNTIME_OUTPUT_DIRECTORY" "${OUTPUT_DIRECTORY}")