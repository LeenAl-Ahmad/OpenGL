











glm::vec3 rotationSpeed = { 0.0f, 0.05f, 0.0f };
for (auto mesh : meshes)
{
	mesh->Render(camera.GetProjection()* camera.GetView());
}