BUILD_DIR = dist

build: main.c
	if [ ! -d ${CURDIR}/${BUILD_DIR} ]; then \
  		echo "Build"; \
  		mkdir ./${BUILD_DIR}; \
  	else \
  	  	echo "Rebuild"; \
  	  	rm -R ./${BUILD_DIR}; \
  	  	mkdir ./${BUILD_DIR}; \
  	fi
	gcc ./main.c -o ./${BUILD_DIR}/main -pthread
	cd ${BUILD_DIR} && ./main

run:
	cd ${BUILD_DIR} && ./main
