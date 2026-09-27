#pragma once

// Status global tiap fitur ViraBot — dipakai bareng oleh
// ViraBotLayer.cpp (UI toggle) dan semua file di src/hooks/
struct ViraBotState {
    static inline bool noclip = false;
    static inline bool speedhack = false;
    static inline bool hitboxShow = false;
    static inline bool autoClick = false;
};
