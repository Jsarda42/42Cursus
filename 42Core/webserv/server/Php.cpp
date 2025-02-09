#include "Php.hpp"

Php::Php()
{
}

Php::~Php()
{
}

void Php::createEnv(ParsedData &parsedData, std::string &filePath)
{
	std::string body = parsedData.getRequestBody();

	env_["SCRIPT_FILENAME"] = filePath;
	env_["REQUEST_METHOD"] = parsedData.getRequestMethod();
	env_["QUERY_STRING"] = parsedData.getRequestArgs();
	env_["REDIRECT_STATUS"] = "200";
	env_["BODY"] = body;
	env_["CONTENT_LENGTH"] = Lib::to_string(body.size());
	env_["CONTENT_TYPE"] =  parsedData.getContentType();
}

char **Php::getEnv()
{
	char **env = new char *[env_.size() + 1];
	size_t i = 0;
	for (std::map<std::string, std::string>::iterator it = env_.begin(); it != env_.end(); ++it, ++i)
	{
		std::string env_entry = it->first + "=" + it->second;
		env[i] = new char[env_entry.size() + 1];
		std::strcpy(env[i], env_entry.c_str());
	}
	env[i] = NULL;
	return env;
}

// Variable globale pour stocker le PID du processus enfant
pid_t child_pid = -1;

// Gestionnaire de signal pour le timeout
void timeoutHandler(int sig)
{
	(void)sig;
	if (child_pid > 0)
	{
		// Tente de tuer le processus enfant
		kill(child_pid, SIGKILL);
	}
}

std::string Php::askPhp()
{
	char **env = getEnv();

	std::string body = env_["BODY"];

	// Crée un pipe pour la communication parent-enfant
	int pipeIn[2];  // Pour envoyer le body à php-cgi
	int pipeOut[2]; // Pour récupérer la sortie de php-cgi
	if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1)
	{
		perror("pipe");
		return "";
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return "";
	}

	if (child_pid == 0)
	{
		// Processus enfant

		// Redirige l'entrée standard vers le pipeIn[0]
		dup2(pipeIn[0], STDIN_FILENO);
		close(pipeIn[1]); // Ferme l'écriture du pipeIn

		// Redirige la sortie standard vers le pipeOut[1]
		dup2(pipeOut[1], STDOUT_FILENO);
		close(pipeOut[0]); // Ferme la lecture du pipeOut

		// Exécute php-cgi avec les variables d'environnement
		char *argv[] = {const_cast<char *>("php-cgi"), NULL};
		execve("/usr/bin/php-cgi", argv, env);

		// Si execve échoue
		perror("execve");
		exit(1);
	}
	else
	{
		// Processus parent

		// Configure le gestionnaire de signal pour le timeout
		struct sigaction sa;
		sa.sa_handler = timeoutHandler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);

		// Configure un délai de 3 secondes
		alarm(5);

		// Ferme les extrémités inutilisées des pipes
		close(pipeIn[0]);
		close(pipeOut[1]);

		// Envoie le body à php-cgi via pipeIn
		write(pipeIn[1], body.c_str(), body.size());
		close(pipeIn[1]); // Ferme l'écriture après envoi

		// Lit la sortie de php-cgi depuis pipeOut
		std::string result;
		char buffer[1024];
		ssize_t bytesRead;
		while ((bytesRead = read(pipeOut[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytesRead] = '\0';
			result += buffer;
		}
		close(pipeOut[0]);

		// Attend la fin du processus enfant
		int status;
		pid_t w = waitpid(child_pid, &status, 0);
		if (w == -1)
		{
			perror("waitpid");
		}

		// Désactive le timeout
		alarm(0);

		// Libère les variables d'environnement
		for (size_t i = 0; env[i] != NULL; ++i)
			delete[] env[i];
		delete[] env;

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL)
		{
			// Le processus a été tué à cause du timeout
			return "Time out";
		}

		return result;
	}
}

