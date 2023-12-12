/*
 * For a detailed explanation regarding each configuration property and type check, visit:
 * https://jestjs.io/docs/en/configuration.html
 */

export default {
  clearMocks: true,
  collectCoverage: true,
  collectCoverageFrom: [
    'src/**/*.{js,ts,jsx,tsx}',
  ],
  coveragePathIgnorePatterns: [
    '/node_modules/',
    '/test/',
    '/src/index.ts',
    '/src/module/index.ts',
  ],
  coverageProvider: 'v8',
  preset: 'ts-jest',
  testEnvironment: 'node',
  testMatch: [
    '**/test/**/*(spec|test).[jt]s?(x)',
    '**/?(*.)+(spec|test).[tj]s?(x)',
  ],
};
