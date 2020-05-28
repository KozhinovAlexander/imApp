#
# Copyrigth: Alexander Kozhinov
# E-Mail: AlexanderKozhinov@yandex.com
#

cmake_minimum_required(VERSION 3.5)

set(MODULE_FOLDER_NAME "app")

include_directories("${imApp_SOURCE_DIR}/${MODULE_FOLDER_NAME}/include")

# add_library(${MODULE_FOLDER_NAME}
#             WorkerThread.cpp
#             )

# target_link_libraries(${MODULE_FOLDER_NAME} PRIVATE Qt5::Widgets)
