#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
	sf::RenderWindow window{ sf::VideoMode(1280, 720), "softpack" };
	window.setFramerateLimit(60);

	ImGui::SFML::Init(window);

	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	sf::Clock deltaClock{};

	while (window.isOpen()) {
		sf::Event event{};

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::DockSpaceOverViewport();
		ImGui::ShowDemoWindow();

		sf::RenderTexture rt{};
		rt.create(1280, 720);
		rt.clear(sf::Color::Black);

		if (ImGui::Begin("Viewport")) {
			ImGui::Image(rt);
		}
		ImGui::End();

		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;
}
