set(DEPLOYDIR ${CMAKE_BINARY_DIR}/deploy)

function(copy source target)
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${source} DESTINATION ${DEPLOYDIR}/${target})
endfunction()

function(copyfilesonly sourcedir targetdir)
    file(GLOB FILESINDIR "${CMAKE_CURRENT_SOURCE_DIR}/${sourcedir}/[^.]*.*")
	file(COPY ${FILESINDIR} DESTINATION ${DEPLOYDIR}/${targetdir})
endfunction()

function(DepolySourceCode)
	# create exercise directory
	file(MAKE_DIRECTORY ${DEPLOYDIR}/exercises)
	file(WRITE ${DEPLOYDIR}/exercises/CMakeLists.txt "include(\"../libcogra/buildutils/AddAllSubdirectories.cmake\")\nAddAllSubdirectories()")
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/buildutils/CMakeListsDeployTemplate.txt DESTINATION ${DEPLOYDIR})
	file(RENAME ${DEPLOYDIR}/CMakeListsDeployTemplate.txt ${DEPLOYDIR}/CMakeLists.txt)
	
	# libcogra
	copyfilesonly(./ ./libcogra)
	copy(buildutils  ./libcogra)
	copy(doc         ./libcogra)
	copy(libcogra    ./libcogra)
	copy(samples     ./libcogra)
	copy(tests       ./libcogra)
	
	# Some test data
	file(MAKE_DIRECTORY ${DEPLOYDIR}/libcogra/data)
	
	# Contrib
	copyfilesonly(contrib/                       ./libcogra/contrib)
	copy(contrib/CMakeProjects                   ./libcogra/contrib)
	copy(contrib/stb_image 						 ./libcogra/contrib)
	
	# Submodules
	copyfilesonly(contrib/submodules             ./libcogra/contrib/submodules)
	
	# Assimp
	copyfilesonly(contrib/submodules/assimp 	 ./libcogra/contrib/submodules/assimp)
	
	copy(contrib/submodules/assimp/cmake-modules ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/code          ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/contrib       ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/include       ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/packaging     ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/port          ./libcogra/contrib/submodules/assimp)
	copy(contrib/submodules/assimp/scripts       ./libcogra/contrib/submodules/assimp)

	# GLFW
	copyfilesonly(contrib/submodules/glfw        ./libcogra/contrib/submodules/glfw)
	
	copy(contrib/submodules/glfw/CMake           ./libcogra/contrib/submodules/glfw)
	copy(contrib/submodules/glfw/deps            ./libcogra/contrib/submodules/glfw)
	copy(contrib/submodules/glfw/include         ./libcogra/contrib/submodules/glfw)
	copy(contrib/submodules/glfw/src             ./libcogra/contrib/submodules/glfw)
	
	# GLI
	copyfilesonly(contrib/submodules/gli		 ./libcogra/contrib/submodules/gli)
	copy(contrib/submodules/gli/cmake            ./libcogra/contrib/submodules/gli)
	copy(contrib/submodules/gli/external         ./libcogra/contrib/submodules/gli)
	copy(contrib/submodules/gli/gli              ./libcogra/contrib/submodules/gli)
	copy(contrib/submodules/gli/util             ./libcogra/contrib/submodules/gli)
	
	# GLM
	copyfilesonly(contrib/submodules/glm		 ./libcogra/contrib/submodules/glm)
	copy(contrib/submodules/glm/cmake            ./libcogra/contrib/submodules/glm)
	copy(contrib/submodules/glm/glm              ./libcogra/contrib/submodules/glm)
	copy(contrib/submodules/glm/util             ./libcogra/contrib/submodules/glm)
	
	# googletest
	copy(contrib/submodules/googletest           ./libcogra/contrib/submodules)
	
	# imgui
	copy(contrib/submodules/imgui                ./libcogra/contrib/submodules)
	
	# spdlog
	copy(contrib/submodules/spdlog               ./libcogra/contrib/submodules)

	# clip
	copy(contrib/submodules/clip                 ./libcogra/contrib/submodules)
	
	# eigen
	copy(contrib/submodules/eigen/Eigen			 ./libcogra/contrib/submodules/eigen)
	
	# TBB
	copyfilesonly(contrib/submodules/tbb	 ./libcogra/contrib/submodules/tbb)
	copy(contrib/submodules/tbb/include      ./libcogra/contrib/submodules/tbb)
	copy(contrib/submodules/tbb/src          ./libcogra/contrib/submodules/tbb)	
	copy(contrib/submodules/tbb/build        ./libcogra/contrib/submodules/tbb)
	
endfunction()