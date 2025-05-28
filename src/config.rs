// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! OS configuration data.

/// Major release that indicates incompatible changes or significant updates.
pub const VERSION_MAJOR: &str = env!("CARGO_PKG_VERSION_MAJOR");

/// Minor release that indicates new features in a backward-compatible manner.
pub const VERSION_MINOR: &str = env!("CARGO_PKG_VERSION_MINOR");

/// Patch release that indicates bug fixes or minor improvements.
pub const VERSION_PATCH: &str = env!("CARGO_PKG_VERSION_PATCH");

/// Macro to create a version string from the version components.
macro_rules! version_string {
    () => {
        concat!(
            "v",
            env!("CARGO_PKG_VERSION_MAJOR"),
            ".",
            env!("CARGO_PKG_VERSION_MINOR"),
            ".",
            env!("CARGO_PKG_VERSION_PATCH")
        )
    };
}

/// OS version.
pub const VERSION: &str = version_string!();

/// OS name.
pub const NAME: &str = env!("CARGO_PKG_NAME");

/// OS short description.
pub const DESCRIPTION: &str = env!("CARGO_PKG_DESCRIPTION");

/// OS code license.
pub const LICENSE: &str = env!("CARGO_PKG_LICENSE");

/// OS code license details.
pub const LICENSE_DETAILS: &str = r#"
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.
"#;

/// OS authors list.
pub const AUTHORS: &str = env!("CARGO_PKG_AUTHORS");

/// OS repository link.
pub const REPOSITORY: &str = env!("CARGO_PKG_REPOSITORY");
