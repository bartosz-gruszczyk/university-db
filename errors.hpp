#pragma once

enum class ErrorCode {
    Ok,
    InvalidPesel,
    PeselAlreadyExists,
    PeselNotFound,
    InvalidIndexNumber,
    IndexNumberAlreadyExists,
    IndexNumberNotFound,
    InvalidSalary,
    LastNameNotFound,
    NotEmployee,
    CantSaveFile,
    CantOpenFile
};
