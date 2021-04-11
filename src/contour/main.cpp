/**
 * This file is part of the "libterminal" project
 *   Copyright (c) 2019-2020 Christian Parpart <christian@parpart.family>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if defined(CONTOUR_FRONTEND_GUI)
    #include <contour/ContourGuiApp.h>
    using ContourApp = contour::ContourGuiApp;
#else
    #include <contour/ContourApp.h>
    using ContourApp = contour::ContourApp;
#endif

int main(int argc, char const* argv[])
{
    ContourApp app;
    return app.run(argc, argv);
}

