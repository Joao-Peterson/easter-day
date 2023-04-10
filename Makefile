
easterDay : main.c buildDir
	gcc $< -o build/$@

buildDir : 
	@mkdir -p build/