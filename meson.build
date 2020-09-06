project('grota3d', 'c')



cc = meson.get_compiler('c')

main_dependencies=[
	dependency('GL'),
	dependency('GLUT'),
	cc.find_library('dl', required : false),
	cc.find_library('m', required : false),
]

includes = include_directories([
	'src',
	'src/core',
	'src/libs',
	'src/libs/glad/include',
	'src/libs/lua/src'
])

files=files(
	'src/main.c',
	'src/core/mathematics.c',
	'src/core/colors.c',
	'src/core/time.c',
	'src/core/shaders.c',
	'src/libs/glad/src/glad.c'
)
executable('grota3d', files,dependencies : main_dependencies,include_directories : includes)
