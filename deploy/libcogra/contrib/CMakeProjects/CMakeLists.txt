add_subdirectory(imgui)
add_subdirectory(tinyfd)
add_subdirectory(glad)
set_target_properties (imgui PROPERTIES FOLDER cogra/contrib)
set_target_properties (tinyfd PROPERTIES FOLDER cogra/contrib)
set_target_properties (glad PROPERTIES FOLDER cogra/contrib)