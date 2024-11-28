




std::string Mesh::RemoveFolder(std::string& _m)
{
	const size_t last_slash_idx = _m.find_lst_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_m.erase(0, last_slash_idx + 1);
	}
	return _m;
}

#pragma region  Texture Loading
textureDiffuse = Texture();
if (loader.LoadedMaterial[0].map_Kd != "")
{
	textureDiffuse.LoadTexture("" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));
}
else
{
	textureDiffuse.LoadTexture("");
}

textureSpecular = Texture();
if (loader.LoadedMaterials[0].map_Ks != "")
{
	textureSpecular.LoadTexture("" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
}

textureNormal = Texture();
if (loader.LoadedMaterials[0].map_bump != "")
{
	enableNormalMaps = true;
	textureNormal.LoadTexture("" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
}

#pragma endregion

shader->SetInt("EnableNormalMaps", enableNormalMaps);

shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, textureDiffuse.GetTexture());
shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, textureSpecular.GetTexture());
shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, textureNormal.GetTexture());

glm::vec3 rotationSpeed = { 0.0f, 0.05f, 0.0f };
for (auto mesh : meshes)
{
	mesh->Render(camera.GetProjection()* camera.GetView());
}