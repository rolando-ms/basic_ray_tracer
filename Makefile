.PHONY: clean All

All:
	@echo "----------Building project:[ basicRayTracer - Debug ]----------"
	@cd "basicRayTracer" && "$(MAKE)" -f  "basicRayTracer.mk"
clean:
	@echo "----------Cleaning project:[ basicRayTracer - Debug ]----------"
	@cd "basicRayTracer" && "$(MAKE)" -f  "basicRayTracer.mk" clean
