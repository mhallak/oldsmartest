# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "velodyne: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ivelodyne:/home/robil/srvss_ws/src/velodyne/msg;-Istd_msgs:/opt/ros/jade/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(velodyne_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" NAME_WE)
add_custom_target(_velodyne_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "velodyne" "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(velodyne
  "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/velodyne
)

### Generating Services

### Generating Module File
_generate_module_cpp(velodyne
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/velodyne
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(velodyne_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(velodyne_generate_messages velodyne_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(velodyne_generate_messages_cpp _velodyne_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(velodyne_gencpp)
add_dependencies(velodyne_gencpp velodyne_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS velodyne_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(velodyne
  "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/velodyne
)

### Generating Services

### Generating Module File
_generate_module_eus(velodyne
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/velodyne
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(velodyne_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(velodyne_generate_messages velodyne_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(velodyne_generate_messages_eus _velodyne_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(velodyne_geneus)
add_dependencies(velodyne_geneus velodyne_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS velodyne_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(velodyne
  "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/velodyne
)

### Generating Services

### Generating Module File
_generate_module_lisp(velodyne
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/velodyne
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(velodyne_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(velodyne_generate_messages velodyne_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(velodyne_generate_messages_lisp _velodyne_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(velodyne_genlisp)
add_dependencies(velodyne_genlisp velodyne_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS velodyne_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(velodyne
  "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/jade/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/velodyne
)

### Generating Services

### Generating Module File
_generate_module_py(velodyne
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/velodyne
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(velodyne_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(velodyne_generate_messages velodyne_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/robil/srvss_ws/src/velodyne/msg/MultiLaserScan.msg" NAME_WE)
add_dependencies(velodyne_generate_messages_py _velodyne_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(velodyne_genpy)
add_dependencies(velodyne_genpy velodyne_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS velodyne_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/velodyne)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/velodyne
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(velodyne_generate_messages_cpp std_msgs_generate_messages_cpp)

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/velodyne)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/velodyne
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
add_dependencies(velodyne_generate_messages_eus std_msgs_generate_messages_eus)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/velodyne)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/velodyne
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(velodyne_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/velodyne)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/velodyne\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/velodyne
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(velodyne_generate_messages_py std_msgs_generate_messages_py)
