# Author: Dominik Harmim <xharmi00@stud.fit.vutbr.cz>

PACK := xharmi00
DOC_DIR = doc
DOC = documentation.pdf


.PHONY: clean
clean:
	rm -rf $(PACK).zip $(PACK) $(DOC)
	cd $(DOC_DIR) && make clean


.PHONY: pack
pack: $(PACK).zip

$(PACK).zip: doc
	mkdir -p $(PACK)
	cp -R \
		.settings board CMSIS drivers source startup utilities \
		.cproject .project IMP_Project.mex $(DOC) $(PACK)
	zip -r $@ $(PACK)


.PHONY: doc
doc: $(DOC)

.PHONY: $(DOC)
$(DOC):
	cd $(DOC_DIR) && make
	cp $(DOC_DIR)/$(DOC) .
