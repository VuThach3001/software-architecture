# Git Flow Strategy

## Overview

Git Flow is a branching model designed for managing releases and maintaining a clean, organized repository structure. It provides a robust framework for collaboration and version control in software development projects.

## Main Branches

### 🌳 main/master
- **Purpose**: Production-ready code
- **Characteristics**: Always stable and deployable
- **Protection**: Should be protected, no direct commits
- **Tags**: All releases are tagged here (e.g., `v1.0.0`, `v1.2.3`)

### 🌳 develop
- **Purpose**: Integration branch for ongoing development
- **Characteristics**: Contains the latest delivered development changes for the next release
- **Protection**: Should be protected, accepts merges from feature branches
- **State**: May be unstable at times during active development

## Supporting Branches

### 🔧 Feature Branches

**Naming Convention**: `feature/<feature-name>`

**Examples**:
- `feature/user-authentication`
- `feature/payment-integration`
- `feature/dark-mode`

**Workflow**:
```bash
# Create feature branch
git checkout develop
git checkout -b feature/user-authentication

# Work on feature
git add .
git commit -m "Add user login functionality"

# Push to remote
git push origin feature/user-authentication

# Create Pull Request to develop
# After code review and approval, merge to develop
# Delete feature branch after merge
```

**Rules**:
- Branch from: `develop`
- Merge back to: `develop`
- Lifetime: Deleted after merge
- Purpose: Develop new features

### 🚀 Release Branches

**Naming Convention**: `release/<version>`

**Examples**:
- `release/1.0.0`
- `release/2.1.0`
- `release/1.5.0-beta`

**Workflow**:
```bash
# Create release branch
git checkout develop
git checkout -b release/1.0.0

# Perform final testing and bug fixes
git commit -am "Fix minor bugs for release"

# Merge to main
git checkout main
git merge release/1.0.0
git tag -a v1.0.0 -m "Release version 1.0.0"

# Merge back to develop
git checkout develop
git merge release/1.0.0

# Delete release branch
git branch -d release/1.0.0
```

**Rules**:
- Branch from: `develop`
- Merge to: `main` AND `develop`
- Lifetime: Deleted after merge
- Purpose: Prepare for production release
- Activities: Bug fixes, documentation, version bumping

### 🔥 Hotfix Branches

**Naming Convention**: `hotfix/<version>`

**Examples**:
- `hotfix/1.0.1`
- `hotfix/2.1.3`
- `hotfix/critical-security-patch`

**Workflow**:
```bash
# Create hotfix branch from main
git checkout main
git checkout -b hotfix/1.0.1

# Fix the critical bug
git commit -am "Fix critical security vulnerability"

# Merge to main
git checkout main
git merge hotfix/1.0.1
git tag -a v1.0.1 -m "Hotfix version 1.0.1"

# Merge to develop
git checkout develop
git merge hotfix/1.0.1

# Delete hotfix branch
git branch -d hotfix/1.0.1
```

**Rules**:
- Branch from: `main`
- Merge to: `main` AND `develop` (or current release branch)
- Lifetime: Deleted after merge
- Purpose: Fix critical production bugs immediately

## Complete Workflow Example

### Starting a New Feature
```bash
# 1. Update develop branch
git checkout develop
git pull origin develop

# 2. Create feature branch
git checkout -b feature/shopping-cart

# 3. Work on feature
# ... make changes ...
git add .
git commit -m "Implement shopping cart functionality"

# 4. Push to remote
git push origin feature/shopping-cart

# 5. Create Pull Request to develop
# 6. After review, merge and delete branch
```

### Preparing a Release
```bash
# 1. Create release branch
git checkout develop
git pull origin develop
git checkout -b release/1.0.0

# 2. Update version numbers
# ... update version in files ...
git commit -am "Bump version to 1.0.0"

# 3. Test and fix minor bugs
# ... testing and fixes ...

# 4. Merge to main
git checkout main
git pull origin main
git merge release/1.0.0
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin main --tags

# 5. Merge back to develop
git checkout develop
git merge release/1.0.0
git push origin develop

# 6. Delete release branch
git branch -d release/1.0.0
git push origin --delete release/1.0.0
```

### Creating a Hotfix
```bash
# 1. Create hotfix branch
git checkout main
git pull origin main
git checkout -b hotfix/1.0.1

# 2. Fix the bug
# ... make fixes ...
git commit -am "Fix critical payment bug"

# 3. Merge to main
git checkout main
git merge hotfix/1.0.1
git tag -a v1.0.1 -m "Hotfix version 1.0.1"
git push origin main --tags

# 4. Merge to develop
git checkout develop
git merge hotfix/1.0.1
git push origin develop

# 5. Delete hotfix branch
git branch -d hotfix/1.0.1
git push origin --delete hotfix/1.0.1
```

## Best Practices

### ✅ Do's

1. **Write Clear Commit Messages**
   - Use present tense: "Add feature" not "Added feature"
   - Be descriptive but concise
   - Reference issue numbers when applicable

2. **Use Pull Requests**
   - Always use PRs for code review
   - Require at least one approval
   - Run automated tests before merging

3. **Protect Important Branches**
   - Protect `main` and `develop` from direct commits
   - Require PR reviews
   - Enable status checks

4. **Keep Branches Short-Lived**
   - Merge features frequently
   - Delete merged branches
   - Rebase/merge from develop regularly

5. **Tag Releases**
   - Use semantic versioning (e.g., `v1.2.3`)
   - Include release notes
   - Tag only on `main` branch

6. **Sync Regularly**
   ```bash
   git checkout develop
   git pull origin develop
   git checkout feature/my-feature
   git merge develop
   ```

### ❌ Don'ts

1. **Never commit directly to main**
2. **Don't merge unreviewed code**
3. **Avoid long-lived feature branches**
4. **Don't push broken code to develop**
5. **Never rewrite public history**
6. **Don't ignore conflicts**

## Commit Message Guidelines

### Format
```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `chore`: Maintenance tasks

### Examples
```
feat(auth): add JWT authentication

Implement JWT-based authentication system with refresh tokens.
Includes middleware for protecting routes.

Closes #123
```

```
fix(payment): resolve checkout crash on mobile

Fixed null pointer exception when processing payments
on iOS devices.

Fixes #456
```

## Semantic Versioning

Follow semantic versioning for releases: `MAJOR.MINOR.PATCH`

- **MAJOR**: Breaking changes (e.g., `2.0.0`)
- **MINOR**: New features, backward compatible (e.g., `1.3.0`)
- **PATCH**: Bug fixes, backward compatible (e.g., `1.2.1`)

**Examples**:
- `1.0.0` → `1.0.1` (bug fix)
- `1.0.1` → `1.1.0` (new feature)
- `1.1.0` → `2.0.0` (breaking change)

## Branch Protection Rules

### For `main` branch:
- ✅ Require pull request reviews (minimum 1-2 approvals)
- ✅ Require status checks to pass
- ✅ Require branches to be up to date
- ✅ Require linear history
- ✅ Include administrators in restrictions
- ❌ Allow force pushes
- ❌ Allow deletions

### For `develop` branch:
- ✅ Require pull request reviews (minimum 1 approval)
- ✅ Require status checks to pass
- ✅ Dismiss stale reviews
- ❌ Allow force pushes
- ❌ Allow deletions

## Alternative Workflows

### GitHub Flow
- Simpler: Only `main` + feature branches
- Best for: Continuous deployment, web applications
- Process: Create branch → Commit → PR → Deploy → Merge

### Trunk-Based Development
- Very simple: One main branch, short-lived feature branches
- Best for: High-performing teams, CI/CD
- Process: Small commits directly to main or very short-lived branches

### GitLab Flow
- Hybrid approach with environment branches
- Branches: `main` → `pre-production` → `production`
- Best for: Multiple deployment environments

## Tools & Automation

### Git Flow Extensions
```bash
# Install git-flow
# On macOS: brew install git-flow
# On Windows: Download from GitHub

# Initialize
git flow init

# Start feature
git flow feature start my-feature

# Finish feature
git flow feature finish my-feature

# Start release
git flow release start 1.0.0

# Finish release
git flow release finish 1.0.0
```

### Recommended Tools
- **GitHub Actions**: Automate CI/CD
- **GitLab CI**: Continuous integration
- **Jenkins**: Build automation
- **Husky**: Git hooks for pre-commit checks
- **Conventional Commits**: Standardize commit messages

## Quick Reference

| Branch Type | Branch From | Merge To       | Naming      |
| ----------- | ----------- | -------------- | ----------- |
| Feature     | develop     | develop        | `feature/*` |
| Release     | develop     | main + develop | `release/*` |
| Hotfix      | main        | main + develop | `hotfix/*`  |

## Resources

- [Original Git Flow Article by Vincent Driessen](https://nvie.com/posts/a-successful-git-branching-model/)
- [GitHub Flow Guide](https://guides.github.com/introduction/flow/)
- [Atlassian Git Flow Tutorial](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
- [Semantic Versioning](https://semver.org/)

---

**Remember**: The best Git workflow is the one your team agrees upon and follows consistently. Adapt these guidelines to fit your project's needs.
