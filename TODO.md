19.12.2025
- ~~GLTFTexture class~~
- ~~GLTFTexture class~~
- GLTFSkin class
- GLTFScene class
- GLTFSampler class
- GLTFNode class
- GLTFPrimitive class
- GLTFMesh class
- GLTFPBRMetallicRoughness class
- GLTFOcclusionTextureInfo class
- GLTFNormalTextureInfo class
- GLTFMaterial class
- GLTFImage class
- GLTFPerspectiveCamera class
- GLTFOrthographicCamera class
- GLTFCamera class
- GLTFBufferView class
- GLTFBuffer class
- GLTFAsset class
- GLTFAnimationSampler class
- GLTFAnimationTarget class
- GLTFAnimationChannel class
- GLTFAnimation class
- GLTFAccessorSparseValues class
- GLTFAccessorSparseIndices class
- GLTFAccessorSparse class
- GLTFAccessor class

27.11.2025

- Shift all indices by default values (all object modules with object indices).
- Add default objects to the object lists at GLTFLoader construction. The number of the indices must be recalculated and written to the appropriate field near the list.