project('akcemu','cpp')
inc_dir='include'
srcAssembler=run_command('srcAssembler.sh')
sources=srcAssembler.stdout().strip().split('\n')
glfw=dependency('glfw3')
glew=dependency('glew')
sfmlAudio=dependency('sfml-audio')
executable('akcemu',sources:sources,include_directories:inc_dir,dependencies:[glfw,glew,sfmlAudio])