run:
	docker run -d --name gusutfdocker -v $(PWD)/workspace:/root/workspace gusugusu1018/tfdocker:latest
start:
	docker start gusutfdocker
stop:
	docker stop gusutfdocker
rm:
	docker rm gusutfdocker
clean:
	docker stop gusutfdocker && docker rm gusutfdocker
shell:
	docker exec -it gusutfdocker /bin/bash
build:
	docker image build -t gusugusu1018/tfdocker:latest image/.
