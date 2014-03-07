if(__get_git_commit_version)
	return()
endif()
set(__get_git_commit_cersion YES)


function(git_get_commit_version _var)
		if(UNIX)
				execute_process(COMMAND git log -n1 HEAD
						COMMAND head -n1
						COMMAND cut -b8-50
						OUTPUT_VARIABLE _output_git)
		endif()
		set(${_var} ${_output_git} PARENT_SCOPE)
endfunction()