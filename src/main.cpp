// Static C++ web app (Wt) serving the Day 22 portfolio landing page.
#include <Wt/WServer.h>
#include <Wt/WResource.h>
#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// Step 4: route resource that renders static/index.html when "/" is accessed
class IndexResource : public Wt::WResource {
public:
    explicit IndexResource(fs::path file) : file_(std::move(file)) {}
    ~IndexResource() override { beingDeleted(); }

protected:
    void handleRequest(const Wt::Http::Request &, Wt::Http::Response &response) override {
        std::ifstream in(file_, std::ios::binary);
        if (!in) {
            response.setStatus(404);
            response.setMimeType("text/plain");
            response.out() << "index.html not found at: " << file_.string();
            return;
        }
        std::ostringstream buf;
        buf << in.rdbuf();
        response.setMimeType("text/html; charset=utf-8");
        response.out() << buf.str();
    }

private:
    fs::path file_;
};

int main(int argc, char **argv) {
    // Step 2: configure Wt to serve files from the 'static' directory (docroot)
    const fs::path staticDir = fs::absolute("static");
    if (!fs::exists(staticDir / "index.html")) {
        std::cerr << "ERROR: " << (staticDir / "index.html").string()
                  << " not found. Run the server from the project root.\n";
        return 1;
    }

    std::vector<std::string> args;
    if (argc == 1) {
        args = {argv[0], "--docroot", staticDir.string(),
                "--http-address", "0.0.0.0", "--http-port", "8080"};
    } else {
        for (int i = 0; i < argc; ++i) args.emplace_back(argv[i]);
    }
    std::vector<char *> cargs;
    for (auto &a : args) cargs.push_back(a.data());

    try {
        Wt::WServer server(static_cast<int>(cargs.size()), cargs.data(), WTHTTP_CONFIGURATION);

        // Route: "/" -> static/index.html
        server.addResource(std::make_shared<IndexResource>(staticDir / "index.html"), "/");

        if (server.start()) {
            std::cout << "Server running at http://localhost:8080  (Ctrl+C to stop)\n";
            Wt::WServer::waitForShutdown();
            server.stop();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
