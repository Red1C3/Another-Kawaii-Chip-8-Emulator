project('akcemu','cpp')
inc_dir='include'
srcAssembler=run_command('srcAssembler.sh')
sources=srcAssembler.stdout().strip().split('\n')
executable('akcemu',sources:sources,include_directories:inc_dir)