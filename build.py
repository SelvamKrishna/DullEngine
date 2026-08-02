import json
import sys
from pathlib import Path

import pycraft
import pycraft.cli
import pycraft.package

WORKING_DIR = Path(__file__).parent
VENDOR_DIR = WORKING_DIR / "vendor"
CONFIG_KEYS = (
    "project_name",
    "raylib_path",
)


def load_config() -> dict[str, str]:
    config_file = WORKING_DIR / "config.json"
    assert config_file.is_file(), "config.json not found"

    with open(config_file, "r") as f:
        config = json.load(f)

        for key in CONFIG_KEYS:
            if not isinstance(config[key], str):
                pycraft._log.err(f"$h1`{key}`$0 not found in $file`config.json`$0")
                sys.exit(1)

    return config


class ApplicationBuilder:
    def __init__(self):
        self.build_config = None
        self.dev_config = load_config()

    def common_flags(
        self, out_type: pycraft.config.OutputType
    ) -> pycraft.config.CompileFlags:
        return pycraft.config.CompileFlags(
            cc=pycraft.config.Compiler.GXX,
            lang=pycraft.config.Language.CPP,
            version=23,
            includes=(
                WORKING_DIR,
                VENDOR_DIR,
                VENDOR_DIR / "zen-log" / "include",
                VENDOR_DIR / "zen-math" / "include",
            ),
            lib_dirs=(Path(self.dev_config["raylib_path"]),),
            libraries=("raylib", "winmm", "gdi32", "opengl32"),
            out_type=out_type,
        )

    def project(
        self,
        name: str,
        src_dir: Path,
        out_type: pycraft.config.OutputType,
        extra_libs: tuple[str, ...] = (),
    ) -> pycraft.config.ProjectConfig:
        flags = self.common_flags(out_type)
        if extra_libs:
            flags.libraries = (*extra_libs, *flags.libraries)
        return pycraft.config.ProjectConfig(
            name=name,
            flags=flags,
            src_dir=WORKING_DIR / src_dir,
            out_dir=WORKING_DIR / "build",
        )

    def build(self):
        pycraft.init()

        # Validate environment
        assert pycraft.config.get_version() >= 3

        # Ensure dependencies
        pycraft.package.ManualPackage(
            path=Path(self.dev_config["raylib_path"]), link="https://www.raylib.com/"
        ).ensure()

        # Get build config
        self.build_config = pycraft.cli.get_build_config()

        # Build engine library
        engine_proj = self.project(
            name="dull_engine",
            src_dir=WORKING_DIR / "engine",
            out_type=pycraft.config.OutputType.LIB_STATIC,
        )

        engine = pycraft.Builder(engine_proj, self.build_config).build()
        self.build_config.should_clean = False  # Do not clean engine

        pycraft.package.ManualPackage(
            path=engine.parent,
            link="https://github.com/SelvamKrishna/dull_engine",
        ).ensure()

        # Build application
        app_proj = self.project(
            name=self.dev_config["project_name"],
            src_dir=WORKING_DIR / "app",
            out_type=pycraft.config.OutputType.EXECUTABLE,
            extra_libs=(engine.stem,),
        )

        # Generate compile flags (uncomment to generate file VVV)
        with open(WORKING_DIR / "compile_flags.txt", "w") as f:
            f.write("\n".join(app_proj.flags.get_compile_flags()))

        # Add engine's output directory to library search path
        app_proj.flags.lib_dirs = (engine.parent, *app_proj.flags.lib_dirs)

        app = pycraft.Builder(app_proj, self.build_config)
        app.build()

        # Run if requested
        if self.build_config.should_run():
            app.run()

        return app


if __name__ == "__main__":
    _ = ApplicationBuilder().build()
