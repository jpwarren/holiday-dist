# A button app registry

class AppRegistry(dict):
    """
    A registry of apps.

    If an app is registered with the Registry, then it
    will be made available for activation by buttonapp.
    """
    def register(self, appklass):
        app = appklass()
        self.__setitem__(app.name, app)

appregistry = AppRegistry()
