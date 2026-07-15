#include "paths.h"

#include <cstdlib>

namespace hsh {

namespace {
// getenv encapsulé : renvoie une chaîne vide si la variable est absente.
std::string env(const char* name) {
    const char* v = std::getenv(name);
    return v ? std::string(v) : std::string();
}
} // namespace

std::string defaultDataDir() {
    // Emplacement de données de l'application, sous l'organisation « morfredus »
    // (cohérent avec les autres apps de l'écosystème). Choisi pour rester
    // ACCESSIBLE À L'UTILISATEUR (pas /var/lib, réservé au root).
#if defined(_WIN32)
    if (std::string la = env("LOCALAPPDATA"); !la.empty())  return la + "\\morfredus\\HomeServerHub";
    if (std::string pd = env("PROGRAMDATA"); !pd.empty())   return pd + "\\morfredus\\HomeServerHub";
    return "data";
#else
    // Convention XDG : ~/.local/share/morfredus/HomeServerHub.
    if (std::string xdg = env("XDG_DATA_HOME"); !xdg.empty()) return xdg + "/morfredus/HomeServerHub";
    if (std::string home = env("HOME"); !home.empty())        return home + "/.local/share/morfredus/HomeServerHub";
    return "data";
#endif
}

} // namespace hsh
